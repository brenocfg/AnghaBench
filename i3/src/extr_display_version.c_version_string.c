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
 scalar_t__ human_readable_key ; 
 int /*<<< orphan*/  human_readable_version ; 
 int /*<<< orphan*/  loaded_config_file_name ; 
 scalar_t__ loaded_config_file_name_key ; 
 int /*<<< orphan*/  sasprintf (int /*<<< orphan*/ *,char*,int,unsigned char const*) ; 

__attribute__((used)) static int version_string(void *ctx, const unsigned char *val, size_t len) {
    if (human_readable_key)
        sasprintf(&human_readable_version, "%.*s", (int)len, val);
    if (loaded_config_file_name_key)
        sasprintf(&loaded_config_file_name, "%.*s", (int)len, val);
    return 1;
}