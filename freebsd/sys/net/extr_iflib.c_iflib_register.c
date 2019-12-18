#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kobj_t ;
typedef  int /*<<< orphan*/  kobj_class_t ;
typedef  int /*<<< orphan*/ * if_t ;
typedef  TYPE_1__* if_shared_ctx_t ;
typedef  TYPE_2__* if_ctx_t ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_10__ {int /*<<< orphan*/ * ifc_mediap; int /*<<< orphan*/  ifc_media; void* ifc_vlan_detach_event; void* ifc_vlan_attach_event; int /*<<< orphan*/ * ifc_ifp; int /*<<< orphan*/  ifc_dev; TYPE_1__* ifc_sctx; } ;
struct TYPE_9__ {int isc_flags; int /*<<< orphan*/ * isc_driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK_INIT (TYPE_2__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_FIRST ; 
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFLIB_DRIVER_MEDIA ; 
 int /*<<< orphan*/  IFM_IMASK ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  STATE_LOCK_INIT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _iflib_assert (TYPE_1__*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setdev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setflags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_setinitfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setioctlfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setqflushfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setsendqready (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_setsoftc (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  if_setstartfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_settransmitfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_altq_if_start ; 
 int /*<<< orphan*/  iflib_altq_if_transmit ; 
 int /*<<< orphan*/  iflib_if_init ; 
 int /*<<< orphan*/  iflib_if_ioctl ; 
 int /*<<< orphan*/  iflib_if_qflush ; 
 int /*<<< orphan*/  iflib_if_transmit ; 
 int /*<<< orphan*/  iflib_media_change ; 
 int /*<<< orphan*/  iflib_media_status ; 
 int /*<<< orphan*/  iflib_vlan_register ; 
 int /*<<< orphan*/  iflib_vlan_unregister ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_class_compile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_config ; 
 int /*<<< orphan*/  vlan_unconfig ; 

__attribute__((used)) static int
iflib_register(if_ctx_t ctx)
{
	if_shared_ctx_t sctx = ctx->ifc_sctx;
	driver_t *driver = sctx->isc_driver;
	device_t dev = ctx->ifc_dev;
	if_t ifp;

	_iflib_assert(sctx);

	CTX_LOCK_INIT(ctx);
	STATE_LOCK_INIT(ctx, device_get_nameunit(ctx->ifc_dev));
	ifp = ctx->ifc_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "can not allocate ifnet structure\n");
		return (ENOMEM);
	}

	/*
	 * Initialize our context's device specific methods
	 */
	kobj_init((kobj_t) ctx, (kobj_class_t) driver);
	kobj_class_compile((kobj_class_t) driver);

	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	if_setsoftc(ifp, ctx);
	if_setdev(ifp, dev);
	if_setinitfn(ifp, iflib_if_init);
	if_setioctlfn(ifp, iflib_if_ioctl);
#ifdef ALTQ
	if_setstartfn(ifp, iflib_altq_if_start);
	if_settransmitfn(ifp, iflib_altq_if_transmit);
	if_setsendqready(ifp);
#else
	if_settransmitfn(ifp, iflib_if_transmit);
#endif
	if_setqflushfn(ifp, iflib_if_qflush);
	if_setflags(ifp, IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST);

	ctx->ifc_vlan_attach_event =
		EVENTHANDLER_REGISTER(vlan_config, iflib_vlan_register, ctx,
							  EVENTHANDLER_PRI_FIRST);
	ctx->ifc_vlan_detach_event =
		EVENTHANDLER_REGISTER(vlan_unconfig, iflib_vlan_unregister, ctx,
							  EVENTHANDLER_PRI_FIRST);

	if ((sctx->isc_flags & IFLIB_DRIVER_MEDIA) == 0) {
		ctx->ifc_mediap = &ctx->ifc_media;
		ifmedia_init(ctx->ifc_mediap, IFM_IMASK,
		    iflib_media_change, iflib_media_status);
	}
	return (0);
}