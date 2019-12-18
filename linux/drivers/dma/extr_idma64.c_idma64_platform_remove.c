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
struct platform_device {int dummy; } ;
struct idma64_chip {int dummy; } ;

/* Variables and functions */
 int idma64_remove (struct idma64_chip*) ; 
 struct idma64_chip* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int idma64_platform_remove(struct platform_device *pdev)
{
	struct idma64_chip *chip = platform_get_drvdata(pdev);

	return idma64_remove(chip);
}