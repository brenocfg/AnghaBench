void *fwnode_get_mac_address(struct fwnode_handle *fwnode, char *addr, int alen)
{
	char *res;

	res = fwnode_get_mac_addr(fwnode, "mac-address", addr, alen);
	if (res)
		return res;

	res = fwnode_get_mac_addr(fwnode, "local-mac-address", addr, alen);
	if (res)
		return res;

	return fwnode_get_mac_addr(fwnode, "address", addr, alen);
}