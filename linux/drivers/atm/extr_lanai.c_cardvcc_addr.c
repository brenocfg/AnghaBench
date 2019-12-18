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
typedef  int vci_t ;
struct lanai_dev {int dummy; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int CARDVCC_SIZE ; 
 int /*<<< orphan*/  sram_addr (struct lanai_dev const*,int) ; 

__attribute__((used)) static inline bus_addr_t cardvcc_addr(const struct lanai_dev *lanai,
	vci_t vci)
{
	return sram_addr(lanai, vci * CARDVCC_SIZE);
}