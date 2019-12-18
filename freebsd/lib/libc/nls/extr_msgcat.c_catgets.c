#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct _nls_set_hdr {scalar_t__ __nmsgs; scalar_t__ __index; scalar_t__ __setno; } ;
struct _nls_msg_hdr {scalar_t__ __offset; scalar_t__ __msgno; } ;
struct _nls_cat_hdr {scalar_t__ __msg_txt_offset; scalar_t__ __msg_hdr_offset; scalar_t__ __nsets; } ;
typedef  TYPE_1__* nl_catd ;
struct TYPE_4__ {scalar_t__ __data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  ENOMSG ; 
 TYPE_1__* NLERR ; 
 int /*<<< orphan*/  errno ; 
 int ntohl (int /*<<< orphan*/ ) ; 

char *
catgets(nl_catd catd, int set_id, int msg_id, const char *s)
{
	struct _nls_cat_hdr *cat_hdr;
	struct _nls_msg_hdr *msg_hdr;
	struct _nls_set_hdr *set_hdr;
	int i, l, r, u;

	if (catd == NULL || catd == NLERR) {
		errno = EBADF;
		/* LINTED interface problem */
		return ((char *)s);
	}

	cat_hdr = (struct _nls_cat_hdr *)catd->__data;
	set_hdr = (struct _nls_set_hdr *)(void *)((char *)catd->__data +
	    sizeof(struct _nls_cat_hdr));

	/* binary search, see knuth algorithm b */
	l = 0;
	u = ntohl((u_int32_t)cat_hdr->__nsets) - 1;
	while (l <= u) {
		i = (l + u) / 2;
		r = set_id - ntohl((u_int32_t)set_hdr[i].__setno);

		if (r == 0) {
			msg_hdr = (struct _nls_msg_hdr *)
			    (void *)((char *)catd->__data +
			    sizeof(struct _nls_cat_hdr) +
			    ntohl((u_int32_t)cat_hdr->__msg_hdr_offset));

			l = ntohl((u_int32_t)set_hdr[i].__index);
			u = l + ntohl((u_int32_t)set_hdr[i].__nmsgs) - 1;
			while (l <= u) {
				i = (l + u) / 2;
				r = msg_id -
				    ntohl((u_int32_t)msg_hdr[i].__msgno);
				if (r == 0) {
					return ((char *) catd->__data +
					    sizeof(struct _nls_cat_hdr) +
					    ntohl((u_int32_t)
					    cat_hdr->__msg_txt_offset) +
					    ntohl((u_int32_t)
					    msg_hdr[i].__offset));
				} else if (r < 0) {
					u = i - 1;
				} else {
					l = i + 1;
				}
			}

			/* not found */
			goto notfound;

		} else if (r < 0) {
			u = i - 1;
		} else {
			l = i + 1;
		}
	}

notfound:
	/* not found */
	errno = ENOMSG;
	/* LINTED interface problem */
	return ((char *)s);
}