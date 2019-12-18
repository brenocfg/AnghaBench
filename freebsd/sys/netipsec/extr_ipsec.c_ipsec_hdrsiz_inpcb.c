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
struct secpolicyindex {int dummy; } ;
struct secpolicy {int dummy; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSEC_DIR_OUTBOUND ; 
 struct secpolicy* ipsec_getpcbpolicy (struct inpcb*,int /*<<< orphan*/ ) ; 
 size_t ipsec_hdrsiz_internal (struct secpolicy*) ; 
 int /*<<< orphan*/  ipsec_setspidx_inpcb (struct inpcb*,struct secpolicyindex*,int /*<<< orphan*/ ) ; 
 struct secpolicy* key_allocsp (struct secpolicyindex*,int /*<<< orphan*/ ) ; 
 struct secpolicy* key_allocsp_default () ; 
 int /*<<< orphan*/  key_freesp (struct secpolicy**) ; 
 scalar_t__ key_havesp (int /*<<< orphan*/ ) ; 

size_t
ipsec_hdrsiz_inpcb(struct inpcb *inp)
{
	struct secpolicyindex spidx;
	struct secpolicy *sp;
	size_t sz;

	sp = ipsec_getpcbpolicy(inp, IPSEC_DIR_OUTBOUND);
	if (sp == NULL && key_havesp(IPSEC_DIR_OUTBOUND)) {
		ipsec_setspidx_inpcb(inp, &spidx, IPSEC_DIR_OUTBOUND);
		sp = key_allocsp(&spidx, IPSEC_DIR_OUTBOUND);
	}
	if (sp == NULL)
		sp = key_allocsp_default();
	sz = ipsec_hdrsiz_internal(sp);
	key_freesp(&sp);
	return (sz);
}