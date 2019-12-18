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
 TYPE_1__ h2o_strdup (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  h2o_strtolower (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static h2o_iovec_t strdup_lowercased(const char *s, size_t len)
{
    h2o_iovec_t v = h2o_strdup(NULL, s, len);
    h2o_strtolower(v.base, v.len);
    return v;
}