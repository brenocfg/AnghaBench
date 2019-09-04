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
 char H2O_COMPRESS_HINT_AUTO ; 
 char H2O_COMPRESS_HINT_DISABLE ; 
 char H2O_COMPRESS_HINT_ENABLE ; 
 char H2O_COMPRESS_HINT_ENABLE_BR ; 
 char H2O_COMPRESS_HINT_ENABLE_GZIP ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 scalar_t__ h2o_lcstris (char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char compress_hint_to_enum(const char *val, size_t len)
{
    if (h2o_lcstris(val, len, H2O_STRLIT("on"))) {
        return H2O_COMPRESS_HINT_ENABLE;
    }
    if (h2o_lcstris(val, len, H2O_STRLIT("off"))) {
        return H2O_COMPRESS_HINT_DISABLE;
    }
    if (h2o_lcstris(val, len, H2O_STRLIT("gzip"))) {
        return H2O_COMPRESS_HINT_ENABLE_GZIP;
    }
    if (h2o_lcstris(val, len, H2O_STRLIT("br"))) {
        return H2O_COMPRESS_HINT_ENABLE_BR;
    }
    return H2O_COMPRESS_HINT_AUTO;
}