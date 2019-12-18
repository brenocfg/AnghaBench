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
struct camq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CAMQ ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ camq_init (struct camq*,int) ; 
 int /*<<< orphan*/  free (struct camq*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct camq *
camq_alloc(int size)
{
	struct camq *camq;

	camq = (struct camq *)malloc(sizeof(*camq), M_CAMQ, M_NOWAIT);
	if (camq != NULL) {
		if (camq_init(camq, size) != 0) {
			free(camq, M_CAMQ);
			camq = NULL;
		}
	}
	return (camq);
}