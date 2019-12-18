#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_3__ {scalar_t__ body; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; TYPE_1__ u; } ;
struct tac_handle {TYPE_2__ request; } ;
struct clnt_str {size_t len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int BODYSIZE ; 
 int /*<<< orphan*/  free_str (struct clnt_str*) ; 
 int /*<<< orphan*/  generr (struct tac_handle*,char*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
add_str_16(struct tac_handle *h, u_int16_t *fld, struct clnt_str *cs)
{
	size_t len;

	len = cs->len;
	if (cs->data == NULL)
		len = 0;
	if (len != 0) {
		int offset;

		if (len > 0xffff) {
			generr(h, "Field too long");
			return -1;
		}
		offset = ntohl(h->request.length);
		if (offset + len > BODYSIZE) {
			generr(h, "Message too long");
			return -1;
		}
		memcpy(h->request.u.body + offset, cs->data, len);
		h->request.length = htonl(offset + len);
	}
	*fld = htons(len);
	free_str(cs);
	return 0;
}