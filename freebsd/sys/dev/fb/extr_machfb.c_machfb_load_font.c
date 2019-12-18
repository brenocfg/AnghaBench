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
typedef  int /*<<< orphan*/  video_adapter_t ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int
machfb_load_font(video_adapter_t *adp, int page, int size, int width,
    u_char *data, int c, int count)
{

	return (ENODEV);
}