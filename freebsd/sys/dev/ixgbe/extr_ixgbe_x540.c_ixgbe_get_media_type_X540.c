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
struct ixgbe_hw {int dummy; } ;
typedef  enum ixgbe_media_type { ____Placeholder_ixgbe_media_type } ixgbe_media_type ;

/* Variables and functions */
 int /*<<< orphan*/  UNREFERENCED_1PARAMETER (struct ixgbe_hw*) ; 
 int ixgbe_media_type_copper ; 

enum ixgbe_media_type ixgbe_get_media_type_X540(struct ixgbe_hw *hw)
{
	UNREFERENCED_1PARAMETER(hw);
	return ixgbe_media_type_copper;
}