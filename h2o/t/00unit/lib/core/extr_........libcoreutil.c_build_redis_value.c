#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  BASE64_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_base64_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  h2o_mem_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static h2o_iovec_t build_redis_value(h2o_iovec_t session_data)
{
    h2o_iovec_t value;
    value.base = h2o_mem_alloc(BASE64_LENGTH(session_data.len));
    value.len = h2o_base64_encode(value.base, session_data.base, session_data.len, 1);
    return value;
}