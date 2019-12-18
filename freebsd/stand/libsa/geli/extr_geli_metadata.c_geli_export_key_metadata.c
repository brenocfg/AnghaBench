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
struct preloaded_file {int dummy; } ;
struct keybuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GELI_KEYBUF_SIZE ; 
 int /*<<< orphan*/  MODINFOMD_KEYBUF ; 
 int /*<<< orphan*/  explicit_bzero (struct keybuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_addmetadata (struct preloaded_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct keybuf*) ; 
 int /*<<< orphan*/  free (struct keybuf*) ; 
 int /*<<< orphan*/  geli_export_key_buffer (struct keybuf*) ; 
 struct keybuf* malloc (int /*<<< orphan*/ ) ; 

void
geli_export_key_metadata(struct preloaded_file *kfp)
{
    struct keybuf *keybuf;

    keybuf = malloc(GELI_KEYBUF_SIZE);
    geli_export_key_buffer(keybuf);
    file_addmetadata(kfp, MODINFOMD_KEYBUF, GELI_KEYBUF_SIZE, keybuf);
    explicit_bzero(keybuf, GELI_KEYBUF_SIZE);
    free(keybuf);
}