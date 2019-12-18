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
struct vtblk_softc {int dummy; } ;
struct vtblk_request {int dummy; } ;

/* Variables and functions */
 struct vtblk_request* vtblk_request_bio (struct vtblk_softc*) ; 
 struct vtblk_request* vtblk_request_next_ready (struct vtblk_softc*) ; 

__attribute__((used)) static struct vtblk_request *
vtblk_request_next(struct vtblk_softc *sc)
{
	struct vtblk_request *req;

	req = vtblk_request_next_ready(sc);
	if (req != NULL)
		return (req);

	return (vtblk_request_bio(sc));
}