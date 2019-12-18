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
typedef  char uint8_t ;

/* Variables and functions */
 char* h2o_hpack_encode_int (char*,size_t,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static size_t encode_as_is(uint8_t *dst, const char *s, size_t len)
{
    uint8_t *start = dst;
    *dst = '\0';
    dst = h2o_hpack_encode_int(dst, len, 7);
    memcpy(dst, s, len);
    dst += len;
    return dst - start;
}