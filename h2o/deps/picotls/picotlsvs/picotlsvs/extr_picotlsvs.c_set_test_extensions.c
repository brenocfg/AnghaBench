#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {size_t len; int /*<<< orphan*/ * base; } ;
struct TYPE_5__ {int type; TYPE_1__ data; } ;
typedef  TYPE_2__ ptls_raw_extension_t ;

/* Variables and functions */
 int PICOTLS_VS_TEST_EXTENSION ; 

void set_test_extensions(ptls_raw_extension_t ext[2], uint8_t * data, size_t len)
{
	ext[0].type = PICOTLS_VS_TEST_EXTENSION;
	ext[0].data.base = data;
	ext[0].data.len = len;
	ext[1].type = 0xFFFF;
	ext[1].data.base = NULL;
	ext[1].data.len = 0;
}