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
struct hio {int /*<<< orphan*/ * hio_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_TEMPFAIL ; 
 unsigned int HAST_HIO_MAX ; 
 int MAXPHYS ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct hio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hio_clear (struct hio*) ; 
 int /*<<< orphan*/  hio_disk_list ; 
 int /*<<< orphan*/  hio_disk_list_cond ; 
 int /*<<< orphan*/  hio_disk_list_lock ; 
 int /*<<< orphan*/  hio_free_list ; 
 int /*<<< orphan*/  hio_free_list_cond ; 
 int /*<<< orphan*/  hio_free_list_lock ; 
 int /*<<< orphan*/  hio_free_list_size ; 
 int /*<<< orphan*/  hio_next ; 
 int /*<<< orphan*/  hio_send_list ; 
 int /*<<< orphan*/  hio_send_list_cond ; 
 int /*<<< orphan*/  hio_send_list_lock ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pjdlog_exitx (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static void
init_environment(void)
{
	struct hio *hio;
	unsigned int ii;

	/*
	 * Initialize lists, their locks and theirs condition variables.
	 */
	TAILQ_INIT(&hio_free_list);
	mtx_init(&hio_free_list_lock);
	cv_init(&hio_free_list_cond);
	TAILQ_INIT(&hio_disk_list);
	mtx_init(&hio_disk_list_lock);
	cv_init(&hio_disk_list_cond);
	TAILQ_INIT(&hio_send_list);
	mtx_init(&hio_send_list_lock);
	cv_init(&hio_send_list_cond);

	/*
	 * Allocate requests pool and initialize requests.
	 */
	for (ii = 0; ii < HAST_HIO_MAX; ii++) {
		hio = malloc(sizeof(*hio));
		if (hio == NULL) {
			pjdlog_exitx(EX_TEMPFAIL,
			    "Unable to allocate memory (%zu bytes) for hio request.",
			    sizeof(*hio));
		}
		hio->hio_data = malloc(MAXPHYS);
		if (hio->hio_data == NULL) {
			pjdlog_exitx(EX_TEMPFAIL,
			    "Unable to allocate memory (%zu bytes) for gctl_data.",
			    (size_t)MAXPHYS);
		}
		hio_clear(hio);
		TAILQ_INSERT_HEAD(&hio_free_list, hio, hio_next);
		hio_free_list_size++;
	}
}