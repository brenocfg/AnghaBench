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
typedef  int /*<<< orphan*/  u8 ;
struct iavf_sc {int dummy; } ;
struct iavf_mac_filter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  IXL_FILTER_DEL ; 
 struct iavf_mac_filter* iavf_find_mac_filter (struct iavf_sc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
iavf_del_mac_filter(struct iavf_sc *sc, u8 *macaddr)
{
	struct iavf_mac_filter	*f;

	f = iavf_find_mac_filter(sc, macaddr);
	if (f == NULL)
		return (ENOENT);

	f->flags |= IXL_FILTER_DEL;
	return (0);
}