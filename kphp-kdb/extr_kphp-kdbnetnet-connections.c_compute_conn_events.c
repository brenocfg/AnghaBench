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
struct connection {int flags; } ;

/* Variables and functions */
 int C_NORD ; 
 int C_NOWR ; 
 int C_STOPREAD ; 
 int C_WANTRD ; 
 int C_WANTWR ; 
 int EVT_LEVEL ; 
 int EVT_READ ; 
 int EVT_SPEC ; 
 int EVT_WRITE ; 

__attribute__((used)) static inline int compute_conn_events (struct connection *c) {
  return (((c->flags & (C_WANTRD | C_STOPREAD)) == C_WANTRD) ? EVT_READ : 0) | (c->flags & C_WANTWR ? EVT_WRITE : 0) | EVT_SPEC 
       | (((c->flags & (C_WANTRD | C_NORD)) == (C_WANTRD | C_NORD))
         || ((c->flags & (C_WANTWR | C_NOWR)) == (C_WANTWR | C_NOWR)) ? EVT_LEVEL : 0);
}