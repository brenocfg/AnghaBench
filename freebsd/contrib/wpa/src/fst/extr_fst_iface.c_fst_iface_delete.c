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
struct fst_iface {int /*<<< orphan*/  mb_ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  fst_iface_set_ies (struct fst_iface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct fst_iface*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void fst_iface_delete(struct fst_iface *i)
{
	fst_iface_set_ies(i, NULL);
	wpabuf_free(i->mb_ie);
	os_free(i);
}