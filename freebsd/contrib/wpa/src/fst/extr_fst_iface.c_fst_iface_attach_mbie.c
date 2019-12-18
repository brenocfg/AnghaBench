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
struct wpabuf {int dummy; } ;
struct fst_iface {struct wpabuf* mb_ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

void fst_iface_attach_mbie(struct fst_iface *i, struct wpabuf *mbie)
{
	wpabuf_free(i->mb_ie);
	i->mb_ie = mbie;
}