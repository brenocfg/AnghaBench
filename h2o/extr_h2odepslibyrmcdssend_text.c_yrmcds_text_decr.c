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
typedef  scalar_t__ yrmcds_error ;
typedef  int /*<<< orphan*/  yrmcds ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  textbuf_t ;

/* Variables and functions */
 scalar_t__ YRMCDS_BAD_ARGUMENT ; 
 scalar_t__ YRMCDS_OK ; 
 scalar_t__ check_key (char const*,size_t) ; 
 scalar_t__ send_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  textbuf_append_char (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  textbuf_append_const_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  textbuf_append_string (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  textbuf_append_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textbuf_init (int /*<<< orphan*/ *) ; 

yrmcds_error yrmcds_text_decr(yrmcds* c, const char* key, size_t key_len,
                              uint64_t value, int quiet, uint32_t* serial) {
    if( key == NULL || key_len == 0 || quiet )
        return YRMCDS_BAD_ARGUMENT;

    yrmcds_error ret;
    ret = check_key(key, key_len);
    if( ret != YRMCDS_OK ) return ret;

    textbuf_t buf[1];
    textbuf_init(buf);

    textbuf_append_const_string(buf, "decr ");
    textbuf_append_string(buf, key, key_len);
    textbuf_append_char(buf, ' ');
    textbuf_append_uint64(buf, value);

    return send_command(c, buf, serial);
}