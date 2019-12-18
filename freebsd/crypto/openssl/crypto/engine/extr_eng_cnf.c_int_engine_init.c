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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_init (int /*<<< orphan*/ *) ; 
 scalar_t__ initialized_engines ; 
 scalar_t__ sk_ENGINE_new_null () ; 
 int /*<<< orphan*/  sk_ENGINE_push (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int int_engine_init(ENGINE *e)
{
    if (!ENGINE_init(e))
        return 0;
    if (!initialized_engines)
        initialized_engines = sk_ENGINE_new_null();
    if (!initialized_engines || !sk_ENGINE_push(initialized_engines, e)) {
        ENGINE_finish(e);
        return 0;
    }
    return 1;
}