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
struct bufobj {int /*<<< orphan*/  bo_bsize; struct vnode* bo_private; int /*<<< orphan*/  bo_ops; } ;
struct vnode {int flags; struct vnode* private; int /*<<< orphan*/  v_rdev; struct bufobj v_bufobj; } ;
struct g_vfs_softc {struct bufobj* sc_bo; int /*<<< orphan*/  sc_mtx; } ;
struct g_provider {int /*<<< orphan*/  sectorsize; int /*<<< orphan*/  mediasize; int /*<<< orphan*/  name; } ;
struct g_geom {struct g_vfs_softc* softc; } ;
struct g_consumer {int flags; struct g_consumer* private; int /*<<< orphan*/  v_rdev; struct bufobj v_bufobj; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  ENXIO ; 
 int G_CF_DIRECT_RECEIVE ; 
 int G_CF_DIRECT_SEND ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  curthread ; 
 int g_access (struct vnode*,int,int,int) ; 
 int /*<<< orphan*/  g_attach (struct vnode*,struct g_provider*) ; 
 struct g_provider* g_dev_getprovider (int /*<<< orphan*/ ) ; 
 struct g_vfs_softc* g_malloc (int,int) ; 
 struct vnode* g_new_consumer (struct g_geom*) ; 
 struct g_geom* g_new_geomf (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_vfs_bufops ; 
 int /*<<< orphan*/  g_vfs_class ; 
 int /*<<< orphan*/  g_wither_geom (struct g_geom*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_create_vobject (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
g_vfs_open(struct vnode *vp, struct g_consumer **cpp, const char *fsname, int wr)
{
	struct g_geom *gp;
	struct g_provider *pp;
	struct g_consumer *cp;
	struct g_vfs_softc *sc;
	struct bufobj *bo;
	int error;

	g_topology_assert();

	*cpp = NULL;
	bo = &vp->v_bufobj;
	if (bo->bo_private != vp)
		return (EBUSY);

	pp = g_dev_getprovider(vp->v_rdev);
	if (pp == NULL)
		return (ENOENT);
	gp = g_new_geomf(&g_vfs_class, "%s.%s", fsname, pp->name);
	sc = g_malloc(sizeof(*sc), M_WAITOK | M_ZERO);
	mtx_init(&sc->sc_mtx, "g_vfs", NULL, MTX_DEF);
	sc->sc_bo = bo;
	gp->softc = sc;
	cp = g_new_consumer(gp);
	g_attach(cp, pp);
	error = g_access(cp, 1, wr, wr);
	if (error) {
		g_wither_geom(gp, ENXIO);
		return (error);
	}
	vnode_create_vobject(vp, pp->mediasize, curthread);
	*cpp = cp;
	cp->private = vp;
	cp->flags |= G_CF_DIRECT_SEND | G_CF_DIRECT_RECEIVE;
	bo->bo_ops = g_vfs_bufops;
	bo->bo_private = cp;
	bo->bo_bsize = pp->sectorsize;

	return (error);
}