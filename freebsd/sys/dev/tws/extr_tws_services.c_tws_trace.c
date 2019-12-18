#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int64_t ;
typedef  size_t u_int16_t ;
struct tws_trace_rec {int linenum; void* val2; void* val1; int /*<<< orphan*/  desc; int /*<<< orphan*/  func; int /*<<< orphan*/  fname; } ;
struct TYPE_2__ {size_t head; size_t tail; size_t volatile depth; int overflow; scalar_t__ q; } ;
struct tws_softc {scalar_t__ is64bit; TYPE_1__ trace_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWS_TRACE_DESC_LEN ; 
 int /*<<< orphan*/  TWS_TRACE_FNAME_LEN ; 
 int /*<<< orphan*/  TWS_TRACE_FUNC_LEN ; 
 int /*<<< orphan*/  printf (char*,int,char const*,char const*,char*,void*,void*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void
tws_trace(const char *file, const char *fun, int linenum,
          struct tws_softc *sc, char *desc, u_int64_t val1, u_int64_t val2)
{ 


    struct tws_trace_rec *rec = (struct tws_trace_rec *)sc->trace_q.q;
    volatile u_int16_t head, tail;
    char fmt[256];

    head = sc->trace_q.head;
    tail = sc->trace_q.tail;
/*
    getnanotime(&rec[tail].ts);
*/
    strncpy(rec[tail].fname, file, TWS_TRACE_FNAME_LEN);
    strncpy(rec[tail].func, fun, TWS_TRACE_FUNC_LEN);
    rec[tail].linenum = linenum;
    strncpy(rec[tail].desc, desc, TWS_TRACE_DESC_LEN);
    rec[tail].val1 = val1;
    rec[tail].val2 = val2;

    tail = (tail+1) % sc->trace_q.depth;

    if ( head == tail ) { 
        sc->trace_q.overflow = 1;
        sc->trace_q.head = (head+1) % sc->trace_q.depth;
    }
    sc->trace_q.tail = tail;

/*
    tws_circular_q_insert(sc, &sc->trace_q, 
                              &rec, sizeof(struct tws_trace_rec));
*/
    if ( sc->is64bit )
        strcpy(fmt, "%05d:%s::%s :%s: 0x%016lx : 0x%016lx \n");
    else
        strcpy(fmt, "%05d:%s::%s :%s: 0x%016llx : 0x%016llx \n");

/*  
    printf("%05d:%s::%s :%s: 0x%016llx : 0x%016llx \n", 
            linenum, file, fun, desc, val1, val2);
*/
    printf(fmt, linenum, file, fun, desc, val1, val2);
}