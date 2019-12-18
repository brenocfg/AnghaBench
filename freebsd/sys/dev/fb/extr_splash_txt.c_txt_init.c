#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_adapter_t ;
struct TYPE_2__ {scalar_t__ data_size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__ txt_decoder ; 

__attribute__((used)) static int
txt_init(video_adapter_t *adp)
{

	/* Ensure that the image data exists. */
	if (txt_decoder.data == NULL || txt_decoder.data_size <= 0) {
		printf("splash_txt: No ASCII bitmap file found\n");
		return (ENODEV);
	}
	return (0);
}