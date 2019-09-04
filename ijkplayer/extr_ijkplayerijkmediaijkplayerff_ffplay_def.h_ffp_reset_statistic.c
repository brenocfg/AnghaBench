#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tcp_read_sampler; } ;
typedef  TYPE_1__ FFStatistic ;

/* Variables and functions */
 int /*<<< orphan*/  FFP_TCP_READ_SAMPLE_RANGE ; 
 int /*<<< orphan*/  SDL_SpeedSampler2Reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) inline static void ffp_reset_statistic(FFStatistic *dcc)
{
    memset(dcc, 0, sizeof(FFStatistic));
    SDL_SpeedSampler2Reset(&dcc->tcp_read_sampler, FFP_TCP_READ_SAMPLE_RANGE);
}