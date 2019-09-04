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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

size_t h2o_stringify_protocol_version(char *dst, int version)
{
    char *p = dst;

    if (version < 0x200) {
        assert(version <= 0x109);
#define PREFIX "HTTP/1."
        memcpy(p, PREFIX, sizeof(PREFIX) - 1);
        p += sizeof(PREFIX) - 1;
#undef PREFIX
        *p++ = '0' + (version & 0xff);
    } else {
#define PROTO "HTTP/2"
        memcpy(p, PROTO, sizeof(PROTO) - 1);
        p += sizeof(PROTO) - 1;
#undef PROTO
    }

    *p = '\0';
    return p - dst;
}