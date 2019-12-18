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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  quicly_stream_frame_t ;

/* Variables and functions */
 int /*<<< orphan*/  quicly_decode_stream_frame (int /*<<< orphan*/  const,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_mozquic(void)
{
    quicly_stream_frame_t frame;
    static const char *mess = "\xc5\0\0\0\0\0\0\xb6\x16\x03";
    const uint8_t *p = (void *)mess, type_flags = *p++;
    quicly_decode_stream_frame(type_flags, &p, p + 9, &frame);
}