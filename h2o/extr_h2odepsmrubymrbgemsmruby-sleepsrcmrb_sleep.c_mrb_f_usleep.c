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
typedef  scalar_t__ time_t ;
struct timeval {scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_fixnum_value (scalar_t__) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usleep (scalar_t__) ; 

__attribute__((used)) static mrb_value
mrb_f_usleep(mrb_state *mrb, mrb_value self)
{
    mrb_int usec;
#ifdef _WIN32
    FILETIME st_ft,ed_ft;
    unsigned __int64 st_time = 0;
    unsigned __int64 ed_time = 0;
#else
    struct timeval st_tm,ed_tm;
#endif
    time_t slp_tm;

#ifdef _WIN32
    GetSystemTimeAsFileTime(&st_ft);
#else
    gettimeofday(&st_tm, NULL);
#endif

    /* not implemented forever sleep (called without an argument)*/
    mrb_get_args(mrb, "i", &usec);

    if (usec >= 0) {
        usleep(usec);
    } else {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "time interval must not be negative integer");
    }

#ifdef _WIN32
    GetSystemTimeAsFileTime(&ed_ft);

    st_time |= st_ft.dwHighDateTime;
    st_time <<=32;
    st_time |= st_ft.dwLowDateTime;
    ed_time |= ed_ft.dwHighDateTime;
    ed_time <<=32;
    ed_time |= ed_ft.dwLowDateTime;

    slp_tm = (ed_time - st_time) / 10;
#else
    gettimeofday(&ed_tm, NULL);

    if (st_tm.tv_usec > ed_tm.tv_usec) {
        slp_tm = 1000000 + ed_tm.tv_usec - st_tm.tv_usec;
    }
    else {
        slp_tm = ed_tm.tv_usec - st_tm.tv_usec;
    }
#endif

    return mrb_fixnum_value(slp_tm);
}