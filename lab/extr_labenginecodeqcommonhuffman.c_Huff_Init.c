#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* tree; TYPE_1__* lhead; int /*<<< orphan*/  blocNode; TYPE_1__* nodeList; TYPE_1__** loc; TYPE_1__* ltail; } ;
struct TYPE_6__ {TYPE_4__ compressor; TYPE_4__ decompressor; } ;
typedef  TYPE_2__ huffman_t ;
typedef  int /*<<< orphan*/  huff_t ;
struct TYPE_5__ {size_t symbol; int /*<<< orphan*/ * right; int /*<<< orphan*/  left; int /*<<< orphan*/  parent; int /*<<< orphan*/ * prev; int /*<<< orphan*/  next; scalar_t__ weight; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 size_t NYT ; 

void Huff_Init(huffman_t *huff) {

	Com_Memset(&huff->compressor, 0, sizeof(huff_t));
	Com_Memset(&huff->decompressor, 0, sizeof(huff_t));

	// Initialize the tree & list with the NYT node 
	huff->decompressor.tree = huff->decompressor.lhead = huff->decompressor.ltail = huff->decompressor.loc[NYT] = &(huff->decompressor.nodeList[huff->decompressor.blocNode++]);
	huff->decompressor.tree->symbol = NYT;
	huff->decompressor.tree->weight = 0;
	huff->decompressor.lhead->next = huff->decompressor.lhead->prev = NULL;
	huff->decompressor.tree->parent = huff->decompressor.tree->left = huff->decompressor.tree->right = NULL;

	// Add the NYT (not yet transmitted) node into the tree/list */
	huff->compressor.tree = huff->compressor.lhead = huff->compressor.loc[NYT] =  &(huff->compressor.nodeList[huff->compressor.blocNode++]);
	huff->compressor.tree->symbol = NYT;
	huff->compressor.tree->weight = 0;
	huff->compressor.lhead->next = huff->compressor.lhead->prev = NULL;
	huff->compressor.tree->parent = huff->compressor.tree->left = huff->compressor.tree->right = NULL;
}