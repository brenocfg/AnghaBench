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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  textbuf_t ;
typedef  char* nbuf ;

/* Variables and functions */
 int /*<<< orphan*/  textbuf_append_string (int /*<<< orphan*/ *,char*,size_t) ; 

__attribute__((used)) static void
textbuf_append_uint64(textbuf_t* buf, uint64_t n) {
    // UINT64_MAX = 18446744073709551615 -> char[20]
    char nbuf[20];
    char* pos = (nbuf) + 20;

    do {
        pos--;
        uint64_t m = n % 10;
        n /= 10;
        *pos = (char)('0' + m);
    } while( n != 0 );

    textbuf_append_string(buf, pos, (size_t)(nbuf - pos + 20));
}