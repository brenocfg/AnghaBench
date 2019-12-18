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
typedef  int /*<<< orphan*/  u16 ;
struct ace_device {scalar_t__ baseaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  in_le16 (scalar_t__) ; 

__attribute__((used)) static u16 ace_in_le16(struct ace_device *ace, int reg)
{
	return in_le16(ace->baseaddr + reg);
}