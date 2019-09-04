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
struct tl_saved_query {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TL_ERROR_AIO_FAIL ; 
 int /*<<< orphan*/  tl_fetch_set_error (char*,int /*<<< orphan*/ ) ; 

void tl_default_aio_fail (struct tl_saved_query *q) {
  tl_fetch_set_error ("Aio/binlog wait error", TL_ERROR_AIO_FAIL);
}