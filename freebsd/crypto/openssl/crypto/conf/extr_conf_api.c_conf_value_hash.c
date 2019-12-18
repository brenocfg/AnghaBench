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
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  section; } ;
typedef  TYPE_1__ CONF_VALUE ;

/* Variables and functions */
 int OPENSSL_LH_strhash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long conf_value_hash(const CONF_VALUE *v)
{
    return (OPENSSL_LH_strhash(v->section) << 2) ^ OPENSSL_LH_strhash(v->name);
}