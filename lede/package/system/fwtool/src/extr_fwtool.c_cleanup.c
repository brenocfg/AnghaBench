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

/* Variables and functions */
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 scalar_t__ firmware_file ; 
 scalar_t__ metadata_file ; 
 scalar_t__ signature_file ; 

__attribute__((used)) static void cleanup(void)
{
	if (signature_file)
		fclose(signature_file);
	if (metadata_file)
		fclose(metadata_file);
	if (firmware_file)
		fclose(firmware_file);
}