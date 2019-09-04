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
 int /*<<< orphan*/  freeReplyObject (void*) ; 
 int /*<<< orphan*/  redisFree (void*) ; 
 int /*<<< orphan*/  test (char*) ; 
 int /*<<< orphan*/  test_cond (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_free_null(void) {
    void *redisCtx = NULL;
    void *reply = NULL;

    test("Don't fail when redisFree is passed a NULL value: ");
    redisFree(redisCtx);
    test_cond(redisCtx == NULL);

    test("Don't fail when freeReplyObject is passed a NULL value: ");
    freeReplyObject(reply);
    test_cond(reply == NULL);
}