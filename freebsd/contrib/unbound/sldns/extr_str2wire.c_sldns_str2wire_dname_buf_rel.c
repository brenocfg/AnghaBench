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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int LDNS_MAX_DOMAINLEN ; 
 scalar_t__ LDNS_MAX_LABELLEN ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERR_DOMAINNAME_OVERFLOW ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERR_DOMAINNAME_UNDERFLOW ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERR_EMPTY_LABEL ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERR_LABEL_OVERFLOW ; 
 int LDNS_WIREPARSE_ERR_OK ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERR_SYNTAX_BAD_ESCAPE ; 
 int RET_ERR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sldns_parse_escape (scalar_t__*,char const**) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int sldns_str2wire_dname_buf_rel(const char* str, uint8_t* buf,
	size_t* olen, int* rel)
{
	size_t len;

	const char *s;
	uint8_t *q, *pq, label_len;

	if(rel) *rel = 0;
	len = strlen((char*)str);
	/* octet representation can make strings a lot longer than actual length */
	if (len > LDNS_MAX_DOMAINLEN * 4) {
		return RET_ERR(LDNS_WIREPARSE_ERR_DOMAINNAME_OVERFLOW, 0);
	}
	if (0 == len) {
		return RET_ERR(LDNS_WIREPARSE_ERR_DOMAINNAME_UNDERFLOW, 0);
	}

	/* root label */
	if (1 == len && *str == '.') {
		if(*olen < 1)
			return RET_ERR(LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL, 0);
		buf[0] = 0;
		*olen = 1;
		return LDNS_WIREPARSE_ERR_OK;
	}

	/* get on with the rest */

	/* s is on the current character in the string
         * pq points to where the labellength is going to go
         * label_len keeps track of the current label's length
	 * q builds the dname inside the buf array
	 */
	len = 0;
	if(*olen < 1)
		return RET_ERR(LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL, 0);
	q = buf+1;
	pq = buf;
	label_len = 0;
	for (s = str; *s; s++, q++) {
		if (q >= buf + *olen)
			return RET_ERR(LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL, q-buf);
		if (q > buf + LDNS_MAX_DOMAINLEN)
			return RET_ERR(LDNS_WIREPARSE_ERR_DOMAINNAME_OVERFLOW, q-buf);
		switch (*s) {
		case '.':
			if (label_len > LDNS_MAX_LABELLEN) {
				return RET_ERR(LDNS_WIREPARSE_ERR_LABEL_OVERFLOW, q-buf);
			}
			if (label_len == 0) {
				return RET_ERR(LDNS_WIREPARSE_ERR_EMPTY_LABEL, q-buf);
			}
			len += label_len + 1;
			*q = 0;
			*pq = label_len;
			label_len = 0;
			pq = q;
			break;
		case '\\':
			/* octet value or literal char */
			s += 1;
			if (!sldns_parse_escape(q, &s)) {
				*q = 0;
				return RET_ERR(LDNS_WIREPARSE_ERR_SYNTAX_BAD_ESCAPE, q-buf);
			}
			s -= 1;
			label_len++;
			break;
		default:
			*q = (uint8_t)*s;
			label_len++;
		}
	}

	/* add root label if last char was not '.' */
	if(label_len != 0) {
		if(rel) *rel = 1;
		if (q >= buf + *olen)
			return RET_ERR(LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL, q-buf);
		if (q > buf + LDNS_MAX_DOMAINLEN) {
			return RET_ERR(LDNS_WIREPARSE_ERR_DOMAINNAME_OVERFLOW, q-buf);
		}
                if (label_len > LDNS_MAX_LABELLEN) {
                        return RET_ERR(LDNS_WIREPARSE_ERR_LABEL_OVERFLOW, q-buf);
                }
                if (label_len == 0) { /* label_len 0 but not . at end? */
                        return RET_ERR(LDNS_WIREPARSE_ERR_EMPTY_LABEL, q-buf);
                }
		len += label_len + 1;
		*pq = label_len;
		*q = 0;
	}
	len++;
	*olen = len;

	return LDNS_WIREPARSE_ERR_OK;
}