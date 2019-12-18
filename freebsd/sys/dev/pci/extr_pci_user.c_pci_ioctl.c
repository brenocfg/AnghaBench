#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  union pci_conf_union {int dummy; } pci_conf_union ;
typedef  int u_long ;
struct thread {int dummy; } ;
struct pci_match_conf {int num_matches; size_t offset; size_t match_buf_len; size_t num_patterns; int pat_buf_len; void* status; int /*<<< orphan*/  generation; int /*<<< orphan*/  matches; int /*<<< orphan*/  patterns; } ;
struct pci_map {int pm_size; int /*<<< orphan*/  pm_value; } ;
struct TYPE_13__ {int /*<<< orphan*/  pc_func; int /*<<< orphan*/  pc_dev; int /*<<< orphan*/  pc_bus; int /*<<< orphan*/  pc_domain; } ;
struct pci_list_vpd_io {TYPE_5__ plvi_sel; } ;
struct TYPE_10__ {int /*<<< orphan*/  pc_func; int /*<<< orphan*/  pc_dev; int /*<<< orphan*/  pc_bus; } ;
struct pci_io_old {int pi_reg; int pi_data; int /*<<< orphan*/  pi_width; TYPE_2__ pi_sel; } ;
struct TYPE_12__ {int /*<<< orphan*/  pc_func; int /*<<< orphan*/  pc_dev; int /*<<< orphan*/  pc_bus; int /*<<< orphan*/  pc_domain; } ;
struct pci_io {int pi_reg; int pi_data; TYPE_4__ pi_sel; int /*<<< orphan*/  pi_width; } ;
struct TYPE_15__ {char* pd_name; int /*<<< orphan*/  pd_unit; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct pci_devinfo {TYPE_7__ conf; TYPE_1__ cfg; } ;
struct pci_conf_io {int num_matches; size_t offset; size_t match_buf_len; size_t num_patterns; int pat_buf_len; void* status; int /*<<< orphan*/  generation; int /*<<< orphan*/  matches; int /*<<< orphan*/  patterns; } ;
struct TYPE_14__ {int /*<<< orphan*/  pc_func; int /*<<< orphan*/  pc_dev; int /*<<< orphan*/  pc_bus; int /*<<< orphan*/  pc_domain; } ;
struct pci_bar_mmap {int pbm_flags; TYPE_6__ pbm_sel; } ;
struct TYPE_11__ {int /*<<< orphan*/  pc_func; int /*<<< orphan*/  pc_dev; int /*<<< orphan*/  pc_bus; int /*<<< orphan*/  pc_domain; } ;
struct pci_bar_io {int pbi_length; int /*<<< orphan*/  pbi_enabled; int /*<<< orphan*/  pbi_base; int /*<<< orphan*/  pbi_reg; TYPE_3__ pbi_sel; } ;
struct devlist {int dummy; } ;
struct cdev {int dummy; } ;
typedef  int pci_addr_t ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOTTY ; 
 int EPERM ; 
 int FWRITE ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PCIIO_BAR_MMAP_RW ; 
#define  PCIOCATTACHED 139 
#define  PCIOCBARMMAP 138 
#define  PCIOCGETBAR 137 
#define  PCIOCGETCONF 136 
#define  PCIOCGETCONF32 135 
#define  PCIOCGETCONF_OLD 134 
#define  PCIOCGETCONF_OLD32 133 
#define  PCIOCLISTVPD 132 
#define  PCIOCREAD 131 
#define  PCIOCREAD_OLD 130 
#define  PCIOCWRITE 129 
#define  PCIOCWRITE_OLD 128 
 void* PCI_GETCONF_ERROR ; 
 void* PCI_GETCONF_LAST_DEVICE ; 
 void* PCI_GETCONF_LIST_CHANGED ; 
 void* PCI_GETCONF_MORE_DEVS ; 
 size_t PCI_MAXNAMELEN ; 
 struct pci_devinfo* STAILQ_FIRST (struct devlist*) ; 
 struct pci_devinfo* STAILQ_NEXT (struct pci_devinfo*,int /*<<< orphan*/ ) ; 
 int copyin (int /*<<< orphan*/ ,struct pci_match_conf*,int) ; 
 int copyout (union pci_conf_union*,int /*<<< orphan*/ ,size_t) ; 
 char* device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int device_is_attached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct pci_match_conf*,int /*<<< orphan*/ ) ; 
 struct pci_match_conf* malloc (int,int /*<<< orphan*/ ,int) ; 
 size_t min (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pci_bar_enabled (int /*<<< orphan*/ *,struct pci_map*) ; 
 int pci_bar_mmap (int /*<<< orphan*/ *,struct pci_bar_mmap*) ; 
 int /*<<< orphan*/  pci_conf_for_copyout (TYPE_7__*,union pci_conf_union*,int) ; 
 int /*<<< orphan*/  pci_conf_io_init (struct pci_match_conf*,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_conf_io_update_data (struct pci_match_conf*,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_conf_match (int,struct pci_match_conf*,int,TYPE_7__*) ; 
 size_t pci_conf_size (int) ; 
 struct devlist pci_devq ; 
 struct pci_map* pci_find_bar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pci_find_dbsf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_generation ; 
 int /*<<< orphan*/  pci_links ; 
 int pci_list_vpd (int /*<<< orphan*/ *,struct pci_list_vpd_io*) ; 
 int pci_match_conf_size (int) ; 
 size_t pci_numdevs ; 
 void* pci_read_config (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static int
pci_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int flag, struct thread *td)
{
	device_t pcidev;
	const char *name;
	struct devlist *devlist_head;
	struct pci_conf_io *cio = NULL;
	struct pci_devinfo *dinfo;
	struct pci_io *io;
	struct pci_bar_io *bio;
	struct pci_list_vpd_io *lvio;
	struct pci_match_conf *pattern_buf;
	struct pci_map *pm;
	struct pci_bar_mmap *pbm;
	size_t confsz, iolen;
	int error, ionum, i, num_patterns;
	union pci_conf_union pcu;
#ifdef PRE7_COMPAT
	struct pci_io iodata;
	struct pci_io_old *io_old;

	io_old = NULL;
#endif

	if (!(flag & FWRITE)) {
		switch (cmd) {
		case PCIOCGETCONF:
#ifdef COMPAT_FREEBSD32
		case PCIOCGETCONF32:
#endif
#ifdef PRE7_COMPAT
		case PCIOCGETCONF_OLD:
#ifdef COMPAT_FREEBSD32
		case PCIOCGETCONF_OLD32:
#endif
#endif
		case PCIOCGETBAR:
		case PCIOCLISTVPD:
			break;
		default:
			return (EPERM);
		}
	}


	switch (cmd) {
	case PCIOCGETCONF:
#ifdef COMPAT_FREEBSD32
	case PCIOCGETCONF32:
#endif
#ifdef PRE7_COMPAT
	case PCIOCGETCONF_OLD:
#ifdef COMPAT_FREEBSD32
	case PCIOCGETCONF_OLD32:
#endif
#endif
		cio = malloc(sizeof(struct pci_conf_io), M_TEMP,
		    M_WAITOK | M_ZERO);
		pci_conf_io_init(cio, data, cmd);
		pattern_buf = NULL;
		num_patterns = 0;
		dinfo = NULL;

		cio->num_matches = 0;

		/*
		 * If the user specified an offset into the device list,
		 * but the list has changed since they last called this
		 * ioctl, tell them that the list has changed.  They will
		 * have to get the list from the beginning.
		 */
		if ((cio->offset != 0)
		 && (cio->generation != pci_generation)){
			cio->status = PCI_GETCONF_LIST_CHANGED;
			error = 0;
			goto getconfexit;
		}

		/*
		 * Check to see whether the user has asked for an offset
		 * past the end of our list.
		 */
		if (cio->offset >= pci_numdevs) {
			cio->status = PCI_GETCONF_LAST_DEVICE;
			error = 0;
			goto getconfexit;
		}

		/* get the head of the device queue */
		devlist_head = &pci_devq;

		/*
		 * Determine how much room we have for pci_conf structures.
		 * Round the user's buffer size down to the nearest
		 * multiple of sizeof(struct pci_conf) in case the user
		 * didn't specify a multiple of that size.
		 */
		confsz = pci_conf_size(cmd);
		iolen = min(cio->match_buf_len - (cio->match_buf_len % confsz),
		    pci_numdevs * confsz);

		/*
		 * Since we know that iolen is a multiple of the size of
		 * the pciconf union, it's okay to do this.
		 */
		ionum = iolen / confsz;

		/*
		 * If this test is true, the user wants the pci_conf
		 * structures returned to match the supplied entries.
		 */
		if ((cio->num_patterns > 0) && (cio->num_patterns < pci_numdevs)
		 && (cio->pat_buf_len > 0)) {
			/*
			 * pat_buf_len needs to be:
			 * num_patterns * sizeof(struct pci_match_conf)
			 * While it is certainly possible the user just
			 * allocated a large buffer, but set the number of
			 * matches correctly, it is far more likely that
			 * their kernel doesn't match the userland utility
			 * they're using.  It's also possible that the user
			 * forgot to initialize some variables.  Yes, this
			 * may be overly picky, but I hazard to guess that
			 * it's far more likely to just catch folks that
			 * updated their kernel but not their userland.
			 */
			if (cio->num_patterns * pci_match_conf_size(cmd) !=
			    cio->pat_buf_len) {
				/* The user made a mistake, return an error. */
				cio->status = PCI_GETCONF_ERROR;
				error = EINVAL;
				goto getconfexit;
			}

			/*
			 * Allocate a buffer to hold the patterns.
			 */
			pattern_buf = malloc(cio->pat_buf_len, M_TEMP,
			    M_WAITOK);
			error = copyin(cio->patterns, pattern_buf,
			    cio->pat_buf_len);
			if (error != 0) {
				error = EINVAL;
				goto getconfexit;
			}
			num_patterns = cio->num_patterns;
		} else if ((cio->num_patterns > 0)
			|| (cio->pat_buf_len > 0)) {
			/*
			 * The user made a mistake, spit out an error.
			 */
			cio->status = PCI_GETCONF_ERROR;
			error = EINVAL;
                       goto getconfexit;
		}

		/*
		 * Go through the list of devices and copy out the devices
		 * that match the user's criteria.
		 */
		for (cio->num_matches = 0, i = 0,
				 dinfo = STAILQ_FIRST(devlist_head);
		     dinfo != NULL;
		     dinfo = STAILQ_NEXT(dinfo, pci_links), i++) {

			if (i < cio->offset)
				continue;

			/* Populate pd_name and pd_unit */
			name = NULL;
			if (dinfo->cfg.dev)
				name = device_get_name(dinfo->cfg.dev);
			if (name) {
				strncpy(dinfo->conf.pd_name, name,
					sizeof(dinfo->conf.pd_name));
				dinfo->conf.pd_name[PCI_MAXNAMELEN] = 0;
				dinfo->conf.pd_unit =
					device_get_unit(dinfo->cfg.dev);
			} else {
				dinfo->conf.pd_name[0] = '\0';
				dinfo->conf.pd_unit = 0;
			}

			if (pattern_buf == NULL ||
			    pci_conf_match(cmd, pattern_buf, num_patterns,
			    &dinfo->conf) == 0) {
				/*
				 * If we've filled up the user's buffer,
				 * break out at this point.  Since we've
				 * got a match here, we'll pick right back
				 * up at the matching entry.  We can also
				 * tell the user that there are more matches
				 * left.
				 */
				if (cio->num_matches >= ionum) {
					error = 0;
					break;
				}

				pci_conf_for_copyout(&dinfo->conf, &pcu, cmd);
				error = copyout(&pcu,
				    (caddr_t)cio->matches +
				    confsz * cio->num_matches, confsz);
				if (error)
					break;
				cio->num_matches++;
			}
		}

		/*
		 * Set the pointer into the list, so if the user is getting
		 * n records at a time, where n < pci_numdevs,
		 */
		cio->offset = i;

		/*
		 * Set the generation, the user will need this if they make
		 * another ioctl call with offset != 0.
		 */
		cio->generation = pci_generation;

		/*
		 * If this is the last device, inform the user so he won't
		 * bother asking for more devices.  If dinfo isn't NULL, we
		 * know that there are more matches in the list because of
		 * the way the traversal is done.
		 */
		if (dinfo == NULL)
			cio->status = PCI_GETCONF_LAST_DEVICE;
		else
			cio->status = PCI_GETCONF_MORE_DEVS;

getconfexit:
		pci_conf_io_update_data(cio, data, cmd);
		free(cio, M_TEMP);
		free(pattern_buf, M_TEMP);

		break;

#ifdef PRE7_COMPAT
	case PCIOCREAD_OLD:
	case PCIOCWRITE_OLD:
		io_old = (struct pci_io_old *)data;
		iodata.pi_sel.pc_domain = 0;
		iodata.pi_sel.pc_bus = io_old->pi_sel.pc_bus;
		iodata.pi_sel.pc_dev = io_old->pi_sel.pc_dev;
		iodata.pi_sel.pc_func = io_old->pi_sel.pc_func;
		iodata.pi_reg = io_old->pi_reg;
		iodata.pi_width = io_old->pi_width;
		iodata.pi_data = io_old->pi_data;
		data = (caddr_t)&iodata;
		/* FALLTHROUGH */
#endif
	case PCIOCREAD:
	case PCIOCWRITE:
		io = (struct pci_io *)data;
		switch(io->pi_width) {
		case 4:
		case 2:
		case 1:
			/* Make sure register is not negative and aligned. */
			if (io->pi_reg < 0 ||
			    io->pi_reg & (io->pi_width - 1)) {
				error = EINVAL;
				break;
			}
			/*
			 * Assume that the user-level bus number is
			 * in fact the physical PCI bus number.
			 * Look up the grandparent, i.e. the bridge device,
			 * so that we can issue configuration space cycles.
			 */
			pcidev = pci_find_dbsf(io->pi_sel.pc_domain,
			    io->pi_sel.pc_bus, io->pi_sel.pc_dev,
			    io->pi_sel.pc_func);
			if (pcidev) {
#ifdef PRE7_COMPAT
				if (cmd == PCIOCWRITE || cmd == PCIOCWRITE_OLD)
#else
				if (cmd == PCIOCWRITE)
#endif
					pci_write_config(pcidev,
							  io->pi_reg,
							  io->pi_data,
							  io->pi_width);
#ifdef PRE7_COMPAT
				else if (cmd == PCIOCREAD_OLD)
					io_old->pi_data =
						pci_read_config(pcidev,
							  io->pi_reg,
							  io->pi_width);
#endif
				else
					io->pi_data =
						pci_read_config(pcidev,
							  io->pi_reg,
							  io->pi_width);
				error = 0;
			} else {
#ifdef COMPAT_FREEBSD4
				if (cmd == PCIOCREAD_OLD) {
					io_old->pi_data = -1;
					error = 0;
				} else
#endif
					error = ENODEV;
			}
			break;
		default:
			error = EINVAL;
			break;
		}
		break;

	case PCIOCGETBAR:
		bio = (struct pci_bar_io *)data;

		/*
		 * Assume that the user-level bus number is
		 * in fact the physical PCI bus number.
		 */
		pcidev = pci_find_dbsf(bio->pbi_sel.pc_domain,
		    bio->pbi_sel.pc_bus, bio->pbi_sel.pc_dev,
		    bio->pbi_sel.pc_func);
		if (pcidev == NULL) {
			error = ENODEV;
			break;
		}
		pm = pci_find_bar(pcidev, bio->pbi_reg);
		if (pm == NULL) {
			error = EINVAL;
			break;
		}
		bio->pbi_base = pm->pm_value;
		bio->pbi_length = (pci_addr_t)1 << pm->pm_size;
		bio->pbi_enabled = pci_bar_enabled(pcidev, pm);
		error = 0;
		break;
	case PCIOCATTACHED:
		error = 0;
		io = (struct pci_io *)data;
		pcidev = pci_find_dbsf(io->pi_sel.pc_domain, io->pi_sel.pc_bus,
				       io->pi_sel.pc_dev, io->pi_sel.pc_func);
		if (pcidev != NULL)
			io->pi_data = device_is_attached(pcidev);
		else
			error = ENODEV;
		break;
	case PCIOCLISTVPD:
		lvio = (struct pci_list_vpd_io *)data;

		/*
		 * Assume that the user-level bus number is
		 * in fact the physical PCI bus number.
		 */
		pcidev = pci_find_dbsf(lvio->plvi_sel.pc_domain,
		    lvio->plvi_sel.pc_bus, lvio->plvi_sel.pc_dev,
		    lvio->plvi_sel.pc_func);
		if (pcidev == NULL) {
			error = ENODEV;
			break;
		}
		error = pci_list_vpd(pcidev, lvio);
		break;

	case PCIOCBARMMAP:
		pbm = (struct pci_bar_mmap *)data;
		if ((flag & FWRITE) == 0 &&
		    (pbm->pbm_flags & PCIIO_BAR_MMAP_RW) != 0)
			return (EPERM);
		pcidev = pci_find_dbsf(pbm->pbm_sel.pc_domain,
		    pbm->pbm_sel.pc_bus, pbm->pbm_sel.pc_dev,
		    pbm->pbm_sel.pc_func);
		error = pcidev == NULL ? ENODEV : pci_bar_mmap(pcidev, pbm);
		break;

	default:
		error = ENOTTY;
		break;
	}

	return (error);
}