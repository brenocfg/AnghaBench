#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ x; TYPE_3__* B; } ;
typedef  TYPE_2__ rpc_point_t ;
struct TYPE_11__ {TYPE_1__* methods; } ;
struct TYPE_9__ {int (* get_port ) (TYPE_3__*) ;int /*<<< orphan*/  (* get_host ) (TYPE_3__*) ;} ;

/* Variables and functions */
 unsigned int htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int stub3 (TYPE_3__*) ; 
 int stub4 (TYPE_3__*) ; 

__attribute__((used)) static int cmp_points (rpc_point_t *A, rpc_point_t *B) {
  unsigned h1 = htonl (A->B->methods->get_host (A->B));
  unsigned h2 = htonl (B->B->methods->get_host (B->B));
  int p1 = A->B->methods->get_port (A->B);
  int p2 = B->B->methods->get_port (B->B);
  if (A->x < B->x) {
    return -1;
  } else if (A->x > B->x) {
    return 1;
  } else if (h1 < h2) {
    return -1;
  } else if (h1 > h2) {
    return 1;
  } else {
    return p1 - p2;
  }
}