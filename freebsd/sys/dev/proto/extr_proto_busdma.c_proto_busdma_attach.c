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
struct proto_softc {int dummy; } ;
struct proto_busdma {int /*<<< orphan*/  sxlck; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PROTO_BUSDMA ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct proto_busdma* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

struct proto_busdma *
proto_busdma_attach(struct proto_softc *sc)
{
	struct proto_busdma *busdma;

	busdma = malloc(sizeof(*busdma), M_PROTO_BUSDMA, M_WAITOK | M_ZERO);
	sx_init(&busdma->sxlck, "proto-busdma");
	return (busdma);
}