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
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU1000_MEM_STSTAT ; 
 int alchemy_rdsmem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int au1200_nand_device_ready(struct nand_chip *this)
{
	return alchemy_rdsmem(AU1000_MEM_STSTAT) & 1;
}