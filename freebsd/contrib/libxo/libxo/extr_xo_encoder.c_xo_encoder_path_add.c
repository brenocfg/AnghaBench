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
 int /*<<< orphan*/  xo_encoder_path ; 
 int /*<<< orphan*/  xo_encoder_setup () ; 
 int /*<<< orphan*/  xo_string_add (int /*<<< orphan*/ *,char const*) ; 

void
xo_encoder_path_add (const char *path)
{
    xo_encoder_setup();

    if (path)
	xo_string_add(&xo_encoder_path, path);
}