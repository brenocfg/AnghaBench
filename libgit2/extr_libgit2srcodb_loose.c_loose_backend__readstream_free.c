#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  zstream; int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ loose_readstream ;
typedef  int /*<<< orphan*/  git_odb_stream ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_futils_mmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_zstream_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void loose_backend__readstream_free(git_odb_stream *_stream)
{
	loose_readstream *stream = (loose_readstream *)_stream;

	git_futils_mmap_free(&stream->map);
	git_zstream_free(&stream->zstream);
	git__free(stream);
}