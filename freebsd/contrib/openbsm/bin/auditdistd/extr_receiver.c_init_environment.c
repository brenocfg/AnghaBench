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
struct adreq {int dummy; } ;

/* Variables and functions */
 scalar_t__ ADIST_BUF_SIZE ; 
 unsigned int ADIST_QUEUE_SIZE ; 
 int /*<<< orphan*/  EX_TEMPFAIL ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct adreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adist_disk_list ; 
 int /*<<< orphan*/  adist_disk_list_cond ; 
 int /*<<< orphan*/  adist_disk_list_lock ; 
 int /*<<< orphan*/  adist_free_list ; 
 int /*<<< orphan*/  adist_free_list_cond ; 
 int /*<<< orphan*/  adist_free_list_lock ; 
 int /*<<< orphan*/  adist_send_list ; 
 int /*<<< orphan*/  adist_send_list_cond ; 
 int /*<<< orphan*/  adist_send_list_lock ; 
 int /*<<< orphan*/  adr_next ; 
 int /*<<< orphan*/  adreq_clear (struct adreq*) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *) ; 
 struct adreq* malloc (scalar_t__) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pjdlog_exitx (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void
init_environment(void)
{
	struct adreq *adreq;
	unsigned int ii;

	TAILQ_INIT(&adist_free_list);
	mtx_init(&adist_free_list_lock);
	cv_init(&adist_free_list_cond);
	TAILQ_INIT(&adist_disk_list);
	mtx_init(&adist_disk_list_lock);
	cv_init(&adist_disk_list_cond);
	TAILQ_INIT(&adist_send_list);
	mtx_init(&adist_send_list_lock);
	cv_init(&adist_send_list_cond);

	for (ii = 0; ii < ADIST_QUEUE_SIZE; ii++) {
		adreq = malloc(sizeof(*adreq) + ADIST_BUF_SIZE);
		if (adreq == NULL) {
			pjdlog_exitx(EX_TEMPFAIL,
			    "Unable to allocate %zu bytes of memory for adreq object.",
			    sizeof(*adreq) + ADIST_BUF_SIZE);
		}
		adreq_clear(adreq);
		TAILQ_INSERT_TAIL(&adist_free_list, adreq, adr_next);
	}
}