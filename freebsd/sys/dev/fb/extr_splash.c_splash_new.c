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
typedef  int /*<<< orphan*/  splash_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPLASH_INIT ; 
 int /*<<< orphan*/  splash_arg ; 
 int /*<<< orphan*/  splash_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * splash_decoder ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
splash_new(splash_decoder_t *decoder)
{
	splash_decoder = decoder;
	if (splash_callback != NULL)
		(*splash_callback)(SPLASH_INIT, splash_arg);
}