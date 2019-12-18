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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  SDL_AMediaCodec ;

/* Variables and functions */

__attribute__((used)) static ssize_t SDL_AMediaCodecDummy_writeInputData(SDL_AMediaCodec* acodec, size_t idx, const uint8_t *data, size_t size)
{
    return size;
}