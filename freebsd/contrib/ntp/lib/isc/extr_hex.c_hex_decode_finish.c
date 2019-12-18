#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_3__ {scalar_t__ length; scalar_t__ digits; } ;
typedef  TYPE_1__ hex_decode_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_BADHEX ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_R_UNEXPECTEDEND ; 

__attribute__((used)) static inline isc_result_t
hex_decode_finish(hex_decode_ctx_t *ctx) {
	if (ctx->length > 0)
		return (ISC_R_UNEXPECTEDEND);
	if (ctx->digits != 0)
		return (ISC_R_BADHEX);
	return (ISC_R_SUCCESS);
}