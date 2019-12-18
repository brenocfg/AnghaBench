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
typedef  int /*<<< orphan*/  umode_t ;
typedef  scalar_t__ uint32_t ;
struct tegra_bpmp {int dummy; } ;
struct seqbuf {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEBUGFS_S_IRUSR ; 
 scalar_t__ DEBUGFS_S_ISDIR ; 
 scalar_t__ DEBUGFS_S_IWUSR ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  S_IWUSR ; 
 struct dentry* debugfs_create_dir (char const*,struct dentry*) ; 
 struct dentry* debugfs_create_file (char const*,int /*<<< orphan*/ ,struct dentry*,struct tegra_bpmp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_fops ; 
 int /*<<< orphan*/  seqbuf_eof (struct seqbuf*) ; 
 int seqbuf_read_str (struct seqbuf*,char const**) ; 
 int seqbuf_read_u32 (struct seqbuf*,scalar_t__*) ; 
 int /*<<< orphan*/  seqbuf_seek (struct seqbuf*,int) ; 

__attribute__((used)) static int bpmp_populate_dir(struct tegra_bpmp *bpmp, struct seqbuf *seqbuf,
			     struct dentry *parent, uint32_t depth)
{
	int err;
	uint32_t d, t;
	const char *name;
	struct dentry *dentry;

	while (!seqbuf_eof(seqbuf)) {
		err = seqbuf_read_u32(seqbuf, &d);
		if (err < 0)
			return err;

		if (d < depth) {
			seqbuf_seek(seqbuf, -4);
			/* go up a level */
			return 0;
		} else if (d != depth) {
			/* malformed data received from BPMP */
			return -EIO;
		}

		err = seqbuf_read_u32(seqbuf, &t);
		if (err < 0)
			return err;
		err = seqbuf_read_str(seqbuf, &name);
		if (err < 0)
			return err;

		if (t & DEBUGFS_S_ISDIR) {
			dentry = debugfs_create_dir(name, parent);
			if (!dentry)
				return -ENOMEM;
			err = bpmp_populate_dir(bpmp, seqbuf, dentry, depth+1);
			if (err < 0)
				return err;
		} else {
			umode_t mode;

			mode = t & DEBUGFS_S_IRUSR ? S_IRUSR : 0;
			mode |= t & DEBUGFS_S_IWUSR ? S_IWUSR : 0;
			dentry = debugfs_create_file(name, mode,
						     parent, bpmp,
						     &debugfs_fops);
			if (!dentry)
				return -ENOMEM;
		}
	}

	return 0;
}