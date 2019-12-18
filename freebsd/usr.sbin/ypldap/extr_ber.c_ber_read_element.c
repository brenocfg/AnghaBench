#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  long long u_char ;
struct ber_element {unsigned long be_type; int be_len; int be_class; int be_encoding; long long be_numeric; int be_free; struct ber_element* be_next; struct ber_element* be_sub; int /*<<< orphan*/ * be_val; } ;
struct ber {int fd; int br_rend; int br_rptr; unsigned long (* br_application ) (struct ber_element*) ;} ;
typedef  int ssize_t ;

/* Variables and functions */
 int BER_CLASS_UNIVERSAL ; 
#define  BER_TYPE_BITSTRING 137 
#define  BER_TYPE_BOOLEAN 136 
#define  BER_TYPE_ENUMERATED 135 
#define  BER_TYPE_EOC 134 
#define  BER_TYPE_INTEGER 133 
#define  BER_TYPE_NULL 132 
#define  BER_TYPE_OBJECT 131 
#define  BER_TYPE_OCTETSTRING 130 
#define  BER_TYPE_SEQUENCE 129 
#define  BER_TYPE_SET 128 
 int /*<<< orphan*/  DPRINTF (char*,int,...) ; 
 int /*<<< orphan*/  ECANCELED ; 
 int ULLONG_MAX ; 
 void* ber_get_element (int /*<<< orphan*/ ) ; 
 int ber_getc (struct ber*,long long*) ; 
 int /*<<< orphan*/  ber_read (struct ber*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errno ; 
 int get_id (struct ber*,unsigned long*,int*,int*) ; 
 int get_len (struct ber*,int*) ; 
 void* malloc (int) ; 
 unsigned long stub1 (struct ber_element*) ; 

__attribute__((used)) static ssize_t
ber_read_element(struct ber *ber, struct ber_element *elm)
{
	long long val = 0;
	struct ber_element *next;
	unsigned long type;
	int i, class, cstruct;
	ssize_t len, r, totlen = 0;
	u_char c;

	if ((r = get_id(ber, &type, &class, &cstruct)) == -1)
		return -1;
	DPRINTF("ber read got class %d type %lu, %s\n",
	    class, type, cstruct ? "constructive" : "primitive");
	totlen += r;
	if ((r = get_len(ber, &len)) == -1)
		return -1;
	DPRINTF("ber read element size %zd\n", len);
	totlen += r + len;

	/*
	 * If using an external buffer and the total size of the element
	 * is larger, then the external buffer don't bother to continue.
	 */
	if (ber->fd == -1 && len > ber->br_rend - ber->br_rptr) {
		errno = ECANCELED;
		return -1;
	}

	elm->be_type = type;
	elm->be_len = len;
	elm->be_class = class;

	if (elm->be_encoding == 0) {
		/* try to figure out the encoding via class, type and cstruct */
		if (cstruct)
			elm->be_encoding = BER_TYPE_SEQUENCE;
		else if (class == BER_CLASS_UNIVERSAL)
			elm->be_encoding = type;
		else if (ber->br_application != NULL) {
			/*
			 * Ask the application to map the encoding to a
			 * universal type. For example, a SMI IpAddress
			 * type is defined as 4 byte OCTET STRING.
			 */
			elm->be_encoding = (*ber->br_application)(elm);
		} else
			/* last resort option */
			elm->be_encoding = BER_TYPE_NULL;
	}

	switch (elm->be_encoding) {
	case BER_TYPE_EOC:	/* End-Of-Content */
		break;
	case BER_TYPE_BOOLEAN:
	case BER_TYPE_INTEGER:
	case BER_TYPE_ENUMERATED:
		if (len > (ssize_t)sizeof(long long))
			return -1;
		for (i = 0; i < len; i++) {
			if (ber_getc(ber, &c) != 1)
				return -1;
			val <<= 8;
			val |= c;
		}

		/* sign extend if MSB is set */
		if (val >> ((i - 1) * 8) & 0x80)
			val |= ULLONG_MAX << (i * 8);
		elm->be_numeric = val;
		break;
	case BER_TYPE_BITSTRING:
		elm->be_val = malloc(len);
		if (elm->be_val == NULL)
			return -1;
		elm->be_free = 1;
		elm->be_len = len;
		ber_read(ber, elm->be_val, len);
		break;
	case BER_TYPE_OCTETSTRING:
	case BER_TYPE_OBJECT:
		elm->be_val = malloc(len + 1);
		if (elm->be_val == NULL)
			return -1;
		elm->be_free = 1;
		elm->be_len = len;
		ber_read(ber, elm->be_val, len);
		((u_char *)elm->be_val)[len] = '\0';
		break;
	case BER_TYPE_NULL:	/* no payload */
		if (len != 0)
			return -1;
		break;
	case BER_TYPE_SEQUENCE:
	case BER_TYPE_SET:
		if (elm->be_sub == NULL) {
			if ((elm->be_sub = ber_get_element(0)) == NULL)
				return -1;
		}
		next = elm->be_sub;
		while (len > 0) {
			r = ber_read_element(ber, next);
			if (r == -1)
				return -1;
			len -= r;
			if (len > 0 && next->be_next == NULL) {
				if ((next->be_next = ber_get_element(0)) ==
				    NULL)
					return -1;
			}
			next = next->be_next;
		}
		break;
	}
	return totlen;
}