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
typedef  int /*<<< orphan*/  uint32_t ;
struct vtballoon_softc {int /*<<< orphan*/  vtballoon_deflate_vq; int /*<<< orphan*/  vtballoon_inflate_vq; int /*<<< orphan*/  vtballoon_td; int /*<<< orphan*/ * vtballoon_page_frames; int /*<<< orphan*/  vtballoon_pages; int /*<<< orphan*/  vtballoon_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INTR_TYPE_MISC ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VTBALLOON_LOCK_INIT (struct vtballoon_softc*,int /*<<< orphan*/ ) ; 
 int VTBALLOON_PAGES_PER_REQUEST ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct vtballoon_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int kthread_add (int /*<<< orphan*/ ,struct vtballoon_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  virtio_set_feature_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int virtio_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_enable_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtballoon_add_sysctl (struct vtballoon_softc*) ; 
 int vtballoon_alloc_virtqueues (struct vtballoon_softc*) ; 
 int /*<<< orphan*/  vtballoon_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtballoon_feature_desc ; 
 int /*<<< orphan*/  vtballoon_negotiate_features (struct vtballoon_softc*) ; 
 int /*<<< orphan*/  vtballoon_thread ; 

__attribute__((used)) static int
vtballoon_attach(device_t dev)
{
	struct vtballoon_softc *sc;
	int error;

	sc = device_get_softc(dev);
	sc->vtballoon_dev = dev;

	VTBALLOON_LOCK_INIT(sc, device_get_nameunit(dev));
	TAILQ_INIT(&sc->vtballoon_pages);

	vtballoon_add_sysctl(sc);

	virtio_set_feature_desc(dev, vtballoon_feature_desc);
	vtballoon_negotiate_features(sc);

	sc->vtballoon_page_frames = malloc(VTBALLOON_PAGES_PER_REQUEST *
	    sizeof(uint32_t), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (sc->vtballoon_page_frames == NULL) {
		error = ENOMEM;
		device_printf(dev,
		    "cannot allocate page frame request array\n");
		goto fail;
	}

	error = vtballoon_alloc_virtqueues(sc);
	if (error) {
		device_printf(dev, "cannot allocate virtqueues\n");
		goto fail;
	}

	error = virtio_setup_intr(dev, INTR_TYPE_MISC);
	if (error) {
		device_printf(dev, "cannot setup virtqueue interrupts\n");
		goto fail;
	}

	error = kthread_add(vtballoon_thread, sc, NULL, &sc->vtballoon_td,
	    0, 0, "virtio_balloon");
	if (error) {
		device_printf(dev, "cannot create balloon kthread\n");
		goto fail;
	}

	virtqueue_enable_intr(sc->vtballoon_inflate_vq);
	virtqueue_enable_intr(sc->vtballoon_deflate_vq);

fail:
	if (error)
		vtballoon_detach(dev);

	return (error);
}