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
struct TYPE_2__ {int /*<<< orphan*/  last_map_key; } ;
typedef  TYPE_1__ parser_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sasprintf (int /*<<< orphan*/ *,char*,size_t,unsigned char const*) ; 

__attribute__((used)) static int stdin_map_key(void *context, const unsigned char *key, size_t len) {
    parser_ctx *ctx = context;
    FREE(ctx->last_map_key);
    sasprintf(&(ctx->last_map_key), "%.*s", len, key);
    return 1;
}