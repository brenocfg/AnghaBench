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

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_FRAME_TYPE_PATH_CHALLENGE ; 
 int /*<<< orphan*/  QUICLY_FRAME_TYPE_PATH_RESPONSE ; 
 int /*<<< orphan*/  QUICLY_PATH_CHALLENGE_DATA_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

uint8_t *quicly_encode_path_challenge_frame(uint8_t *dst, int is_response, const uint8_t *data)
{
    *dst++ = is_response ? QUICLY_FRAME_TYPE_PATH_RESPONSE : QUICLY_FRAME_TYPE_PATH_CHALLENGE;
    memcpy(dst, data, QUICLY_PATH_CHALLENGE_DATA_LEN);
    dst += QUICLY_PATH_CHALLENGE_DATA_LEN;
    return dst;
}