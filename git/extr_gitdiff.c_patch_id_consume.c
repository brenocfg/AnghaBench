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
struct patch_id_t {int patchlen; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_SHA1_Update (int /*<<< orphan*/ ,char*,int) ; 
 int remove_space (char*,unsigned long) ; 

__attribute__((used)) static void patch_id_consume(void *priv, char *line, unsigned long len)
{
	struct patch_id_t *data = priv;
	int new_len;

	new_len = remove_space(line, len);

	git_SHA1_Update(data->ctx, line, new_len);
	data->patchlen += new_len;
}