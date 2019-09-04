#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ len; scalar_t__ base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 scalar_t__ BASE64_LENGTH (scalar_t__) ; 
 scalar_t__ h2o_base64_encode (scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ h2o_mem_alloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static h2o_iovec_t build_redis_key(h2o_iovec_t session_id, h2o_iovec_t prefix)
{
    h2o_iovec_t key;
    key.base = h2o_mem_alloc(prefix.len + BASE64_LENGTH(session_id.len));
    if (prefix.len != 0) {
        memcpy(key.base, prefix.base, prefix.len);
    }
    key.len = prefix.len;
    key.len += h2o_base64_encode(key.base + key.len, session_id.base, session_id.len, 1);
    return key;
}