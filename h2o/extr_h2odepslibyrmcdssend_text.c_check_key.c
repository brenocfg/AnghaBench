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

/* Variables and functions */
 size_t MAX_KEY_LENGTH ; 
 int /*<<< orphan*/  YRMCDS_BAD_KEY ; 
 int /*<<< orphan*/  YRMCDS_OK ; 

__attribute__((used)) static inline yrmcds_error
check_key(const char* key, size_t key_len) {
    if( key_len > MAX_KEY_LENGTH )
        return YRMCDS_BAD_KEY;

    size_t i;
    for( i = 0; i < key_len; i++ ) {
        char c = key[i];
        if( c <= ' ' ) return YRMCDS_BAD_KEY;  // SPC and control chars
        if( c == 127 ) return YRMCDS_BAD_KEY;  // DEL
    }

    return YRMCDS_OK;
}