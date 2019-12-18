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
struct targbh_cmd_desc {int max_size; int /*<<< orphan*/ * backing_store; } ;

/* Variables and functions */
 int MAX_BUF_SIZE ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_SCSIBH ; 
 int /*<<< orphan*/  bzero (struct targbh_cmd_desc*,int) ; 
 int /*<<< orphan*/  free (struct targbh_cmd_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct targbh_cmd_desc*
targbhallocdescr()
{
	struct targbh_cmd_desc* descr;

	/* Allocate the targbh_descr structure */
	descr = (struct targbh_cmd_desc *)malloc(sizeof(*descr),
					       M_SCSIBH, M_NOWAIT);
	if (descr == NULL)
		return (NULL);

	bzero(descr, sizeof(*descr));

	/* Allocate buffer backing store */
	descr->backing_store = malloc(MAX_BUF_SIZE, M_SCSIBH, M_NOWAIT);
	if (descr->backing_store == NULL) {
		free(descr, M_SCSIBH);
		return (NULL);
	}
	descr->max_size = MAX_BUF_SIZE;
	return (descr);
}