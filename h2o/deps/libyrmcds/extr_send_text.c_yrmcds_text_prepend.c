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
typedef  int /*<<< orphan*/  yrmcds_error ;
typedef  int /*<<< orphan*/  yrmcds ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXPAND_STR (char*) ; 
 int /*<<< orphan*/  send_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,size_t,char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

yrmcds_error yrmcds_text_prepend(yrmcds* c, const char* key, size_t key_len,
                                 const char* data, size_t data_len,
                                 int quiet, uint32_t* serial) {
    return send_data(c, EXPAND_STR("prepend"), key, key_len, data, data_len,
                     0, 0, 0, quiet, serial);
}