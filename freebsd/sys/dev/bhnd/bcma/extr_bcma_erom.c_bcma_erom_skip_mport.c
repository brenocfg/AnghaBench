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
struct bcma_erom_mport {int dummy; } ;
struct bcma_erom {int dummy; } ;

/* Variables and functions */
 int bcma_erom_parse_mport (struct bcma_erom*,struct bcma_erom_mport*) ; 

__attribute__((used)) static int
bcma_erom_skip_mport(struct bcma_erom *erom)
{
	struct bcma_erom_mport mp;
	return (bcma_erom_parse_mport(erom, &mp));
}