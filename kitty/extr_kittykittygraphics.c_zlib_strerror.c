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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  Z_BUF_ERROR 133 
#define  Z_DATA_ERROR 132 
#define  Z_ERRNO 131 
#define  Z_MEM_ERROR 130 
#define  Z_STREAM_ERROR 129 
#define  Z_VERSION_ERROR 128 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 char const* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const char*
zlib_strerror(int ret) {
#define Z(x) case x: return #x;
    static char buf[128];
    switch(ret) {
        case Z_ERRNO:
            return strerror(errno);
        default:
            snprintf(buf, sizeof(buf)/sizeof(buf[0]), "Unknown error: %d", ret);
            return buf;
        Z(Z_STREAM_ERROR);
        Z(Z_DATA_ERROR);
        Z(Z_MEM_ERROR);
        Z(Z_BUF_ERROR);
        Z(Z_VERSION_ERROR);
    }
#undef Z
}