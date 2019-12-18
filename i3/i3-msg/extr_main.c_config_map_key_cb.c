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
 int /*<<< orphan*/  config_last_key ; 
 int /*<<< orphan*/  sstrndup (char const*,size_t) ; 

__attribute__((used)) static int config_map_key_cb(void *params, const unsigned char *keyVal, size_t keyLen) {
    config_last_key = sstrndup((const char *)keyVal, keyLen);
    return 1;
}